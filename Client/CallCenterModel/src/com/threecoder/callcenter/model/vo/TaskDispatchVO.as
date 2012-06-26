package com.threecoder.callcenter.model.vo
{
	public class TaskDispatchVO implements IVO
	{
		public var taskId :uint = 0;
		public var phoneNumber :String = "";
		public var userNumber :String = "测试";
		public var taskType :Array = new Array();
		public var taskState :uint = 0;
		public var msgType :uint = 2003;
		
		public function TaskDispatchVO()
		{
		}
		
		public function toJson() :String {
			return JSON.stringify( this );
		}
	}
}