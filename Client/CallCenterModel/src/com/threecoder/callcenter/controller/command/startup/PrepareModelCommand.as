package com.threecoder.callcenter.controller.command.startup
{
	import com.threecoder.callcenter.model.proxy.SocketProxy;
	
	import org.puremvc.as3.interfaces.INotification;
	import org.puremvc.as3.patterns.command.SimpleCommand;
	
	public class PrepareModelCommand extends SimpleCommand
	{
		override public function execute( note:INotification ):void {
			var ccSocketProxy :SocketProxy = new SocketProxy();
			
			facade.registerProxy( ccSocketProxy );
			
			ccSocketProxy.connect( "192.168.1.100", 6789 );
			//ccSocketProxy.connect( "localhost", 60000 );
		}
	}
}