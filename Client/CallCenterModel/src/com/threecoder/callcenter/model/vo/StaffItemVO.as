package com.threecoder.callcenter.model.vo
{
	public class StaffItemVO
	{
		[Bindable]
		public var selected :Boolean = false;
		public var name :String;
		public var phoneNumber :String;
		public var department :String;
		public var state :String;
		
		public function StaffItemVO()
		{
		}
	}
}