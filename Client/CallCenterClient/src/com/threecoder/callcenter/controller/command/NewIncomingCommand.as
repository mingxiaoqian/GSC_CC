package com.threecoder.callcenter.controller.command
{
	import com.threecoder.callcenter.view.popup.component.IncomingCallAlert;
	
	import org.puremvc.as3.interfaces.INotification;
	import org.puremvc.as3.patterns.command.SimpleCommand;
	
	public class NewIncomingCommand extends SimpleCommand
	{
		override public function execute( note:INotification ):void {
			var incomingCallAlert :IncomingCallAlert = new IncomingCallAlert();
			incomingCallAlert.open(true);
		}
	}
}