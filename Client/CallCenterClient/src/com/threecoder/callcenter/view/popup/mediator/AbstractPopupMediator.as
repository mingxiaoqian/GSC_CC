package com.threecoder.callcenter.view.popup.mediator
{
	import com.threecoder.callcenter.view.popup.component.IPopup;
	import com.threecoder.callcenter.view.popup.event.PopupActionEvent;
	import com.threecoder.callcenter.view.popup.request.PopupRequest;
	
	import mx.managers.PopUpManager;
	
	import org.puremvc.as3.interfaces.INotification;
	import org.puremvc.as3.patterns.mediator.Mediator;
	import org.puremvc.as3.patterns.observer.Notification;
	
	public class AbstractPopupMediator extends Mediator
	{
		// The request is stored temporarily while the popup is alive 
		// so that the mediator can notify the caller.
		protected var request:PopupRequest;
		
		public function AbstractPopupMediator(name:String)
		{
			super(name);
		}
		
		/**
		 * Override in subclass.
		 * Just create and the concrete popup. 
		 */
		protected function popupFactory():IPopup
		{
			return null;
		}
		
		/**
		 * Called from the handleNotification method when a request notification
		 * is received. Creates the popup with popupFactory(), gives it the data
		 * from the request, calls setEventInterests to add the listeners, then
		 * pops up the popup and optionally centers it.  
		 */
		protected function openPopup( ) : void 
		{
			var popup:IPopup = popupFactory();
			if (popup) {
				popup.setData( request.data );
				setEventInterests( popup );
				PopUpManager.addPopUp( popup, 
					request.parent, 
					request.modal, 
					request.childList );
				if ( request.center ) {
					PopUpManager.centerPopUp( popup );
				}
			}
		}
		
		/**
		 * Called from openPopup when the request is set, before
		 * popping up the popup. Interrogates the popup for the
		 * events it will dispatch and sets listeners for each.
		 */
		protected function setEventInterests( popup:IPopup ):void
		{
			for each ( var interest:String in popup.getEvents() )
			{
				popup.addEventListener( interest, handlePopupAction, false, 0, true );
			}
		}
		
		/**
		 * Subclasses will register a single notification interest,
		 * which will be handled here in the same way for all subclasses.
         */
        override public function handleNotification( note:INotification ):void
        {
            request = note.getBody() as PopupRequest;
            openPopup( );                
        }
		
		/**
		 * Subclasses will set a single notification interest,
		 * which will be handled here in the same way for all subclasses.
		 * The popup will be closed if specified by the event, and then the
		 * caller will be notified with the PopupEvent and the
		 */
		protected function handlePopupAction( event:PopupActionEvent ):void
		{
			var popup:IPopup = event.target as IPopup;
			if ( event.closePopup ) removePopup( popup );
			var note:Notification = new Notification( event.type, event );
			if (request.hasCallback) request.notifyObserver( note );
			request = null;
		}
		
		/**
		 * Called if the PopupActionEvent's closePopup property is true
		 */
		protected function removePopup( popup:IPopup ):void
		{
			PopUpManager.removePopUp( popup );
		}
	}
}