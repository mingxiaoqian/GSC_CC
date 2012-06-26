package com.threecoder.callcenter.view.mediator
{
	import com.threecoder.callcenter.controller.constant.AppConstants;
	import com.threecoder.callcenter.model.constant.ModelConstants;
	import com.threecoder.callcenter.model.proxy.SocketProxy;
	import com.threecoder.callcenter.model.vo.CallerInfoVO;
	import com.threecoder.callcenter.model.vo.SearchStaffVO;
	import com.threecoder.callcenter.model.vo.TaskVO;
	import com.threecoder.callcenter.view.component.IncomingCall;
	import com.threecoder.callcenter.view.event.AppEvent;
	
	import mx.collections.ArrayCollection;
	
	import org.puremvc.as3.interfaces.INotification;
	import org.puremvc.as3.patterns.mediator.Mediator;
	
	public class IncomingCallMediator extends Mediator
	{
		public static const NAME :String = "IncomingCallMediator";
		
		public function IncomingCallMediator( incomingCall :IncomingCall )
		{
			super(NAME, incomingCall);
		}
		
		override public function listNotificationInterests():Array {
			return [ ModelConstants.NEW_INCOMING, 
						ModelConstants.PHONE_NUMBER,
						ModelConstants.CALLER_INFO,
						ModelConstants.SEARCH_RESULT,
						ModelConstants.GET_TASK_TYPE_LIST
						];
		}
		
		override public function handleNotification(notification:INotification):void {
			switch( notification.getName() ) {
				case ModelConstants.NEW_INCOMING:
					sendNotification( AppConstants.MAXIMIZE );
					break;
				case ModelConstants.PHONE_NUMBER:
					incomingCall.phoneNumber = notification.getBody() as String;
					break;
				case ModelConstants.CALLER_INFO:
					incomingCall.department = ( notification.getBody() as CallerInfoVO ).department;
					incomingCall.datetime = ( notification.getBody() as CallerInfoVO ).datetime;
					incomingCall.phoneNumber = ( notification.getBody() as CallerInfoVO ).phoneNumber;
					incomingCall.taskId = ( notification.getBody() as CallerInfoVO ).taskId;
				case ModelConstants.SEARCH_RESULT:
					incomingCall.searchResult = notification.getBody() as ArrayCollection;
					break;
				case ModelConstants.GET_TASK_TYPE_LIST:
					incomingCall.taskTypeList = notification.getBody() as Array;
					break;
				default:
					break;
			}
		}
		
		override public function onRegister():void {
			addListen();
		}
		
		private function addListen():void
		{
			incomingCall.addEventListener(AppEvent.SEARCH_STAFF, handleAppEvent);
			incomingCall.addEventListener(AppEvent.DISPATCH_TASK, handleAppEvent);
			incomingCall.addEventListener(AppEvent.RESERVE_TASK, handleAppEvent);
		}
		
		private function handleAppEvent( event:AppEvent ):void {
			var ccSocketProxy :SocketProxy;
			switch ( event.type ) {
				case AppEvent.SEARCH_STAFF:
					event.stopImmediatePropagation();
					var searchStaffVO :SearchStaffVO = new SearchStaffVO();
					searchStaffVO.nameSpell = event.data as String;
					
					ccSocketProxy = (facade.retrieveProxy( SocketProxy.NAME )) as SocketProxy;
					ccSocketProxy.sendData( searchStaffVO );
					break;
				case AppEvent.DISPATCH_TASK:
				case AppEvent.RESERVE_TASK:
					var taskVO :TaskVO = event.data as TaskVO;
					
					ccSocketProxy = (facade.retrieveProxy( SocketProxy.NAME )) as SocketProxy;
					ccSocketProxy.dispatchTask( taskVO );
					break;
				default:
					break;
			}
		}
		
		private function get incomingCall() :IncomingCall {
			return viewComponent as IncomingCall;
		}
	}
}