package com.threecoder.callcenter.view.popup.mediator
{
	import com.threecoder.callcenter.view.popup.component.CallerPopup;
	import com.threecoder.callcenter.view.popup.component.IPopup;
	import com.threecoder.callcenter.view.popup.request.PopupRequest;

	public class CallerPopupMediator extends AbstractPopupMediator
	{
		public static const NAME :String = "CallerPopupMediator";
		
		public function CallerPopupMediator()
		{
			super(NAME);
		}
		
		override public function listNotificationInterests():Array
		{
			return [ PopupRequest.CALLER_POPUP ];
		}
		override protected function popupFactory():IPopup
		{
			return new CallerPopup();
		}
	}
}