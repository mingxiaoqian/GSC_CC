package com.threecoder.callcenter
{
	import com.threecoder.callcenter.controller.command.NewIncomingCommand;
	import com.threecoder.callcenter.controller.command.startup.StartupCommand;
	import com.threecoder.callcenter.controller.constant.AppConstants;
	
	import org.puremvc.as3.patterns.facade.Facade;
	
	public class ApplicationFacade extends Facade
	{
		public static function getInstance( ) : ApplicationFacade 
		{
			if ( instance == null ) instance = new ApplicationFacade( );
			return instance as ApplicationFacade;
		}
		
		protected override function initializeController():void {
			super.initializeController();
			
			registerCommand( AppConstants.STARTUP, StartupCommand );
			registerCommand( AppConstants.SHOW_INCOMING, NewIncomingCommand );
		}
		
		public function startup( app :CallCenter ):void
		{
			sendNotification( AppConstants.STARTUP, app );
		}
	}
}