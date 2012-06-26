package com.threecoder.callcenter.model.vo
{
	import com.threecoder.callcenter.model.constant.SocketMessageType;

	public class SearchStaffVO implements IVO
	{
		public const msgType :uint = SocketMessageType.DOWN_MSG_TYPE_QUERY_STAFF_INFO_REQUEST;
		public var nameSpell :String = "";
		
		public function SearchStaffVO()
		{
		}
		
		public function toJson():String
		{
			return JSON.stringify( this );
		}
	}
}