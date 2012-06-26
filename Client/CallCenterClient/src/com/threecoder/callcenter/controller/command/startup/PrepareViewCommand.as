package com.threecoder.callcenter.controller.command.startup
{
	import com.threecoder.callcenter.view.mediator.ApplicationMediator;
	import com.threecoder.callcenter.view.mediator.IncomingCallMediator;
	import com.threecoder.callcenter.view.popup.mediator.CallerPopupMediator;
	
	import org.puremvc.as3.interfaces.INotification;
	import org.puremvc.as3.patterns.command.SimpleCommand;
	
	public class PrepareViewCommand extends SimpleCommand
	{
		override public function execute( note:INotification ):void {
			var app :CallCenter = note.getBody() as CallCenter;
			
			facade.registerMediator( new ApplicationMediator( app ) );
			facade.registerMediator( new IncomingCallMediator( app.incomingCall ) );
			
			facade.registerMediator( new CallerPopupMediator() );
		}
	}
}