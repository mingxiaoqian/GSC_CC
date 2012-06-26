package com.threecoder.callcenter.controller.command.caller
{
	import com.threecoder.callcenter.model.proxy.SocketProxy;
	import com.threecoder.callcenter.model.vo.CallerVO;
	import com.threecoder.callcenter.view.popup.event.PopupActionEvent;
	import com.threecoder.callcenter.view.popup.request.PopupRequest;
	
	import org.puremvc.as3.interfaces.INotification;
	import org.puremvc.as3.patterns.command.SimpleCommand;
	
	public class ManageCallerCommand extends SimpleCommand
	{
		private var caller :CallerVO;
		private var socketProxy :SocketProxy;
		
		public function ManageCallerCommand()
		{
			super();
		}
		
		override public function execute( note:INotification ):void {
			socketProxy = facade.retrieveProxy( SocketProxy.NAME ) as SocketProxy;
			
			// Request the popup
			var request:PopupRequest = 
				new PopupRequest( handleEditPopupNote, this );
			request.data.caller = caller;
			sendNotification( PopupRequest.CALLER_POPUP, request );
		}
		
		/**
		 * Handle the popup actions.
		 */
		private function handleEditPopupNote( actionNote:INotification ):void
		{
			var event:PopupActionEvent = PopupActionEvent( actionNote.getBody() );
			caller = CallerVO( event.data );
			switch ( actionNote.getName() ) 
			{
				case PopupActionEvent.ADD:
					socketProxy.addCaller( caller );
					break;
				case PopupActionEvent.CANCEL:
					break;
			}
		}
				
	}
}