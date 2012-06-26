package com.threecoder.callcenter.model.constant
{
	public class SocketMessageType
	{
		public static const UP_MSG_TYPE_DIALOG_POP :uint = 1001;
		public static const UP_MSG_TYPE_PHONE_NUMBER :uint = 1002;
		public static const UP_MSG_TYPE_CALLER_INFO :uint = 1003;
		public static const UP_MSG_TYPE_STAFF_INFO :uint = 1004;
		public static const DOWN_MSG_TYPE_QUERY_STAFF_INFO_REQUEST :uint = 2001;
		public static const DOWN_MSG_TYPE_TASK_DISPATCH :uint = 2003;
		
		public function SocketMessageType()
		{
		}
	}
}