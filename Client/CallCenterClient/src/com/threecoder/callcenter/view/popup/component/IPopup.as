package com.threecoder.callcenter.view.popup.component
{
	import mx.core.IFlexDisplayObject;

	public interface IPopup extends IFlexDisplayObject
	{
		function setData( data:Object ):void;
		function getEvents():Array;
	}
}