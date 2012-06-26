package com.threecoder.callcenter.view.popup.request
{
	import flash.display.DisplayObject;
	
	import mx.core.FlexGlobals;
	import mx.managers.PopUpManagerChildList;
	
	import org.puremvc.as3.patterns.observer.Observer;
	
	/**
	 * PopupRequest carries all the information necessary 
	 * to request a popup be created by its mediator.
	 */
	public class PopupRequest extends Observer
	{
		// Prefix for all request notification names
		private static const NAME:String = "PopupRequest/"; 
		
		public static const CALLER_POPUP :String = NAME + "CallerPopup";
		
		// Request has a callback. (Set by constructor)
		public var hasCallback:Boolean = false;
		
		// Parent in the display list to open the popup over. 
		public var parent:DisplayObject = FlexGlobals.topLevelApplication as DisplayObject;
		
		// Child list to place the popup in 
		public var childList:String = PopUpManagerChildList.PARENT;
		
		// Should the popup be centered? 
		public var center:Boolean = true;
		
		// Should the popup be modal?
		public var modal:Boolean = true;
		
		// Optional data for the popup to use, 
		//such as a title or width and height
		public var data:Object = {};
		
		public function PopupRequest(callback:Function = null, caller:Object = null)
		{
			super(callback, caller);
			hasCallback = ( callback != null && caller != null );
		}
		
		// Convenience method for creating a new Alert Request
		public static function getAlertRequest( message:String,  
												windowTitle:String="Alert", 
												callback:Function=null, 
												caller:Object = null):PopupRequest {
			var request:PopupRequest = new PopupRequest( callback, caller );
			request.childList = PopUpManagerChildList.POPUP;
			request.data.windowTitle = windowTitle;
			request.data.message = message;
			return request;
		}
	}
}