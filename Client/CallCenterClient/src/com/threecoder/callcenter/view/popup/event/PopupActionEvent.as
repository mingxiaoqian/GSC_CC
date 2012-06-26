package com.threecoder.callcenter.view.popup.event
{
	import flash.events.Event;
	
	public class PopupActionEvent extends Event
	{
		private static const NAME :String = "PopupEvent/";
		
		public static const CANCEL:String  = NAME + "cancel";
		public static const OK:String      = NAME + "ok";
		public static const ADD:String     = NAME + "add";
		public static const SAVE:String    = NAME + "save";
		public static const DELETE:String  = NAME + "delete";
		
		public var data :Object;
		public var closePopup :Boolean;
		
		/**
		 * Constructor.
		 * 
		 * Dispatched from a popup, captured by PopupMediatorBase and sent 
		 * back to the original caller for interpretation.
		 */
		public function PopupActionEvent(type:String, data:Object=null, closePopup:Boolean=true)
		{
			super( type );
			this.data = data;
			this.closePopup = closePopup;
		}
	}
}