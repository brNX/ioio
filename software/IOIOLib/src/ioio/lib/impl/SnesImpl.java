package ioio.lib.impl;

import java.io.IOException;

import android.util.Log;

import ioio.lib.api.Snes;
import ioio.lib.api.exception.ConnectionLostException;
import ioio.lib.impl.IncomingState.SnesListener;

public class SnesImpl extends AbstractResource implements Snes ,SnesListener{


	private final int latchPinNum_;
	private final int clkPinNum_;
	private final int dataPinNum_;
	
	private byte[] snesstatus = new byte[2];
	
	public SnesImpl(IOIOImpl ioio,int latchPinNum,int clkPinNum,int dataPinNum) throws ConnectionLostException {
		
		super(ioio);
		
		latchPinNum_=latchPinNum;
		clkPinNum_=clkPinNum;
		dataPinNum_=dataPinNum;
		
		Log.i("SnesImp","new Snes  latch="+latchPinNum+" clock="+clkPinNum+" data="+dataPinNum);
		
	}
	

	@Override
	synchronized public void close() {
		super.close();
		ioio_.closePin(latchPinNum_);
		ioio_.closePin(clkPinNum_);
		ioio_.closePin(dataPinNum_);
		try {
			ioio_.protocol_.setSnesPins(0,0,0);
		} catch (IOException e) {
			e.printStackTrace();
		}
	}

	@Override
	public byte[] readStatus() throws InterruptedException,
			ConnectionLostException {
		return snesstatus;
	}


	@Override
	public void setStatus(byte[] status) {
		assert (status.length == 2);
		snesstatus=status;
	}

}
