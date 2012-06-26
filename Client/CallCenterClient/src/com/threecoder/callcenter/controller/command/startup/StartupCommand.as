package com.threecoder.callcenter.controller.command.startup
{
	import org.puremvc.as3.patterns.command.MacroCommand;
	
	public class StartupCommand extends MacroCommand
	{
		override protected function initializeMacroCommand():void
		{
			addSubCommand( PrepareControllerCommand );
			addSubCommand( PrepareModelCommand );
			addSubCommand( PrepareViewCommand );
		}
	}
}