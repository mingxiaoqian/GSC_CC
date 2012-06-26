package com.threecoder.callcenter.model.vo
{
	public class StaffVO
	{
		public var name :String;
		public var userNumber :String;
		public var callNumber :String;
		public var phoneNumber :String;
		public var department :String;
		
		private var  _stateValue :int;
		private var _stateStr :String = "";
		
		public function StaffVO()
		{
		}
		
		public function set stateValue( stateValue :int ) :void {
			_stateValue = stateValue;
			switch(_stateValue)
			{
				case 0:
				{
					_stateStr = "空闲";
					break;
				}
					
				default:
				{
					break;
				}
			}
		}
		
		public function get state() :String {
			return _stateStr;
		}
	}
}