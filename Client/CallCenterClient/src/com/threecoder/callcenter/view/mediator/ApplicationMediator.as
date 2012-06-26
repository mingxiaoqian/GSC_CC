package com.threecoder.callcenter.view.mediator
{
	import com.threecoder.callcenter.controller.constant.AppConstants;
	import com.threecoder.callcenter.model.constant.ModelConstants;
	import com.threecoder.callcenter.view.constant.ViewConstants;
	import com.threecoder.callcenter.view.event.AppEvent;
	import com.threecoder.callcenter.view.popup.component.IncomingCallAlert;
	
	import org.puremvc.as3.interfaces.INotification;
	import org.puremvc.as3.patterns.mediator.Mediator;
	
	public class ApplicationMediator extends Mediator
	{
		public static const NAME :String = "ApplicationMediator";
		
		public function ApplicationMediator( app :CallCenter )
		{
			super(NAME, app);
		}
		
		override public function onRegister():void {
			addListener();	
		}
		
		private function addListener() :void {
			app.addEventListener(AppEvent.ADD_CALLER, handleAppEvent);
		}
		
		private function handleAppEvent( event :AppEvent ) :void {
			switch( event.type ) {
				case AppEvent.ADD_CALLER:
					sendNotification(AppConstants.MANAGE_CALLER);
					break;
				default:
					break;
			}
		}
		
		private function get app() :CallCenter {
			return viewComponent as CallCenter;
		}
		
		/**
		 * Notifications this Mediator is interested in.
		 */
		override public function listNotificationInterests():Array {
			return [AppConstants.MAXIMIZE];
		}
		
		/**
		 * Handle the notifications this Mediator is interested in.
		 */
		override public function handleNotification( note:INotification ):void {
			switch(note.getName())
			{
				case AppConstants.MAXIMIZE:
					app.maximize();
					app.orderToFront();
					break;
				default:
				{
					break;
				}
			}
		}
	}
}