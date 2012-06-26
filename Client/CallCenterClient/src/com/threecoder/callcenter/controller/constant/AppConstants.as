package com.threecoder.callcenter.controller.constant
{
	public class AppConstants
	{
		// VOCABULARY COMPONENTS
		private static const NAME:String 			= "CallCenter";
		private static const SEP:String 			= "/";
		private static const CC:String 				= NAME + SEP;
		
		// VERBS
		private static const SHOW:String 			= CC + "Show"    + SEP;
		private static const MANAGE :String = CC + "Manage" + SEP;
		
		// NOUNS
		private static const INCOMING :String = "incoming";
		private static const CALLER :String = "Caller";
		
		// NOTIFICATION NAMES
		public static const STARTUP :String 			= CC + "Startup";
		public static const SHOW_INCOMING :String = SHOW + INCOMING;
		public static const MAXIMIZE :String = CC + "Maximize";
		public static const MANAGE_CALLER :String = MANAGE + CALLER; //管理来电者的信息
	}
}