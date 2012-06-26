package com.threecoder.callcenter.controller.command.startup
{
	import com.threecoder.callcenter.controller.command.caller.ManageCallerCommand;
	import com.threecoder.callcenter.controller.constant.AppConstants;
	
	import org.puremvc.as3.interfaces.INotification;
	import org.puremvc.as3.patterns.command.SimpleCommand;
	
	public class PrepareControllerCommand extends SimpleCommand
	{
		public function PrepareControllerCommand()
		{
			super();
		}
		
		override public function execute( note:INotification ):void {
			facade.registerCommand( AppConstants.MANAGE_CALLER, ManageCallerCommand );
		}
	}
}