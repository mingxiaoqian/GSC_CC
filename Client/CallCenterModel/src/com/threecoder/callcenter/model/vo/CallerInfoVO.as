package com.threecoder.callcenter.model.vo
{
	public class CallerInfoVO implements IVO
	{
		public var userId :uint;
		public var phoneNumber :String;
		public var name :String;
		public var department :String;
		public var datetime :String;
		public var taskId :String;
		
		public function CallerInfoVO()
		{
		}
		
		public function toJson() :String {
			return JSON.stringify( this );
		}
	}
}