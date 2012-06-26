package com.threecoder.callcenter.view.event
{
	import flash.events.Event;
	
	public class AppEvent extends Event
	{
		private static const SEP:String 			= "/";
		// VERBS
		private static const SHOW:String 			= "Show"    + SEP;
		private static const SELECT :String = "Select" + SEP;
		private static const DISPATCH :String = "Dispatch" + SEP;
		private static const RESERVE :String = "Reserve" + SEP;
		private static const ADD :String = "Add" + SEP;
		
		// NOUNS
		private static const INCOMING :String = "Incoming";
		private static const STAFF :String = "Staff";
		private static const TASK :String = "Task";
		private static const CALLER :String = "Caller";
		
		// AppEvent types
		public static const CLOSE :String = "close";
		public static const SHOW_INCOMING :String = SHOW + INCOMING;
		public static const SEARCH_STAFF :String = "SearchStaff";
		public static const SELECT_STAFF :String = SELECT + STAFF;
		public static const DISPATCH_TASK :String = DISPATCH + TASK;
		public static const RESERVE_TASK :String = RESERVE + TASK;
		public static const ADD_CALLER :String = ADD + CALLER;
		
		public var data :Object;
		
		public function AppEvent(type:String, bubbles:Boolean=false, cancelable:Boolean=false)
		{
			super(type, bubbles, cancelable);
		}
	}
}