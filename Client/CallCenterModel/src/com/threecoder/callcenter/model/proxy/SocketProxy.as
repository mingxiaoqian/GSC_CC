package com.threecoder.callcenter.model.proxy
{	
	import com.threecoder.callcenter.model.constant.ModelConstants;
	import com.threecoder.callcenter.model.constant.SocketMessageType;
	import com.threecoder.callcenter.model.vo.CallerInfoVO;
	import com.threecoder.callcenter.model.vo.StaffVO;
	import com.threecoder.callcenter.model.vo.TaskDispatchVO;
	
	import flash.events.Event;
	import flash.events.IOErrorEvent;
	import flash.events.ProgressEvent;
	import flash.events.SecurityErrorEvent;
	import flash.net.Socket;
	import flash.utils.ByteArray;
	
	import flashx.textLayout.events.ModelChange;
	import flashx.textLayout.operations.PasteOperation;
	
	import mx.collections.ArrayCollection;
	
	import org.puremvc.as3.patterns.proxy.Proxy;
	
	public class SocketProxy extends Proxy
	{
		// Registered name
		public  static const NAME :String = "SocketProxy";
		
		private static const HEAD_SIZE :uint = 8;
		
		private var _socket :Socket;
		private var host :String;
		private var port :uint;
		
		private var _packLen :int = -1;
		private var _msgType :uint = 0;
		private var _dataLen :uint = 0;
		
		public function SocketProxy()
		{
			super(NAME);
			
			_socket = new Socket();
			addListener();
			
			data = _socket;
		}
		
		private function addListener() :void {
			_socket.addEventListener(Event.CONNECT, onSocketConnect);
			_socket.addEventListener(Event.CLOSE, onSocketClose);
			_socket.addEventListener(ProgressEvent.SOCKET_DATA, onSocketReceive);
			_socket.addEventListener(IOErrorEvent.IO_ERROR, onIOError);
			_socket.addEventListener(SecurityErrorEvent.SECURITY_ERROR, onSocketSecurityError);
			
		}
		
		private function onSocketConnect(e:Event):void
		{
			trace("connect ok..................");
			//var taskDispatchVO :TaskDispatchVO = new TaskDispatchVO();
			//sendData( taskDispatchVO.toJson() );
		}
		
		private function onSocketReceive(e:ProgressEvent):void
		{
			while( _socket.bytesAvailable >= _packLen ) {
				//trace( "avaiable = " + _socket.bytesAvailable + " data = " + _socket.readUTFBytes( _socket.bytesAvailable ) ); 
				if( _packLen == -1 && _socket.bytesAvailable >= HEAD_SIZE ) {
					initHead();
					_packLen = _dataLen + 3;
				}
				if( _packLen == -1 ) {
					return;
				}
				
				if( _socket.bytesAvailable < _packLen ) {
					return;
				}
				
				parseSocketData();
				
				_packLen = -1;
				onSocketReceive( null );
			}

			//sendNotification( ModelConstants.NEW_INCOMING );
		}
		
		private function onSocketClose(e:Event):void {
			
		}
		
		private function onSocketSecurityError(e:SecurityErrorEvent):void {
			trace("security error");
		}
		
		private function onIOError(e:IOErrorEvent):void
		{
			trace("io error");
		}
		
		public function connect( host :String, port :uint ) :void {
			this.host = host;
			this.port = port;

			_socket.connect( host, port );
		}
		
		private function initHead() :void {
			var headStr :String = _socket.readUTFBytes( 4 );
			if( headStr != "HEAD" ) {
				trace("socket data error!");
			}
			
			var dataLenStr :String = _socket.readUTFBytes( 4 );
			_dataLen = parseInt( dataLenStr );
		}
		
		private function parseSocketData() :void {
			var dataStr :String = _socket.readUTFBytes( _dataLen );
			trace("data: " + dataStr);
			var dataObj :Object = JSON.parse( dataStr );
			_msgType = dataObj.msgType;
			
			var tailStr :String = _socket.readUTFBytes( 4 );
			if( tailStr != "END" ) {
				trace("socket data tail error!");
			}
			
			var taskDispatchVO :TaskDispatchVO = new TaskDispatchVO();
			//sendData( taskDispatchVO.toJson() );
			
			switch( _msgType ) {
				case SocketMessageType.UP_MSG_TYPE_DIALOG_POP:
					sendNotification( ModelConstants.NEW_INCOMING );
					break;
				case SocketMessageType.UP_MSG_TYPE_PHONE_NUMBER:
					sendNotification( ModelConstants.PHONE_NUMBER, dataObj.phoneNumber );
					break;
				case SocketMessageType.UP_MSG_TYPE_CALLER_INFO:
					onCallerInfo( dataObj );
					break;
				case SocketMessageType.UP_MSG_TYPE_STAFF_INFO:
					onStaffInfo( dataObj );
					break;
				case SocketMessageType.DOWN_MSG_TYPE_QUERY_STAFF_INFO_REQUEST:
					break;
				case SocketMessageType.DOWN_MSG_TYPE_TASK_DISPATCH:
					break;
				default :
					trace( "message type error!");
					break;
			}
			
		}
		
		private function onStaffInfo( data :Object ) :void {
			var staffInfoArr :Array = data.staffInfo as Array;
			
			if( staffInfoArr ) {
				var ac :ArrayCollection = new ArrayCollection();
				for each(var obj :Object in staffInfoArr ) {
					var staffVO :StaffVO = new StaffVO();
					staffVO.name = obj.name;
					staffVO.department = obj.post;
					staffVO.stateValue = obj.staffState;
					staffVO.phoneNumber = obj.phoneNumber;
					ac.addItem( staffVO );
				}
				
				sendNotification( ModelConstants.SEARCH_RESULT, ac );
			}
		}
		
		private function onCallerInfo( data :Object ) :void {
			var callerInfoVO :CallerInfoVO = new CallerInfoVO();
			callerInfoVO.userId = data.userId;
			callerInfoVO.department = data.department;
			callerInfoVO.phoneNumber = data.phoneNumber;
			if( !data.datetime || data.datetime == "" ) {
				callerInfoVO.datetime = new Date().toString();
			}
			else {
				callerInfoVO.datetime = data.datetime;
			}
			
			sendNotification( ModelConstants.CALLER_INFO, callerInfoVO );
		}
		
		public function sendData( data :String ) :void {
			var temp :ByteArray = new ByteArray();
			temp.writeUTFBytes( data );
			var byteArr :ByteArray = new ByteArray();
			byteArr.writeUTFBytes( "HEAD" );
			byteArr.writeUTFBytes( uintToString( temp.length ) );
			byteArr.writeUTFBytes( data );
			byteArr.writeUTFBytes( "END" );
			_socket.writeBytes( byteArr );
			_socket.flush();
		}
		
		private function uintToString( len :uint ) :String {
			trace( "len = " + len );
			var str :String = "";
			str += uint(len / 1000);
			len %= 1000;
			str += uint(len / 100);
			len %= 100;
			str += uint(len / 10);
			len %= 10;
			str += len;
			
			return str;
		}
	}
}