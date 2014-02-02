package com.motoduino.mduinobt2;

import android.app.Activity;
import android.content.pm.ActivityInfo;
import android.hardware.Sensor;
import android.hardware.SensorEvent;
import android.hardware.SensorEventListener;
import android.hardware.SensorManager;
import android.os.Bundle;
import android.util.Log;
import android.view.Menu;
import android.view.MenuItem;
import android.widget.TextView;


public class sensorcontrol extends Activity implements SensorEventListener
{
	
	// For shake motion detection.
	 private SensorManager sensorMgr;  
	 private float x, y, z;
	 public String btAddress;
	 private TextView xyz_value;
	 private int nStatus;
	 
 	 private static final int SENSOR_STOP 		= 0;
	 private static final int SENSOR_FORWARD 	= 1;
	 private static final int SENSOR_BACKWARD 	= 2;
	 private static final int SENSOR_LEFT 		= 3;
	 private static final int SENSOR_RIGHT 		= 4;
	 
	 @Override
	 public void onCreate(Bundle savedInstanceState)
	 {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.sensorcontrol);
		
        setRequestedOrientation (ActivityInfo.SCREEN_ORIENTATION_LANDSCAPE);        
       	xyz_value = (TextView)findViewById(R.id.sensor_xyz);         	

       	Bundle extras = getIntent().getExtras();
        if(extras != null)
        {
        	btAddress = extras.getString("bluetooth_MAC");
         }
        
        Log.i("sensorcontrol", "DEVICE ADDRESS ="+ btAddress);
        
	    sensorMgr = (SensorManager) getSystemService(SENSOR_SERVICE);
	    
	    nStatus = SENSOR_STOP;
	   	boolean accelSupported = sensorMgr.registerListener(
	   			this,
	   			sensorMgr.getDefaultSensor(SensorManager.SENSOR_ORIENTATION),
	   			SensorManager.SENSOR_DELAY_NORMAL);
     	if (!accelSupported) {
    	    // non accelerometer on this device
    	    sensorMgr.unregisterListener(this); 
     	}
	 }

	 public void onAccuracyChanged(Sensor arg0, int arg1) 
	 {
	 	// TODO Auto-generated method stub
	 }	 

	 private void sendMessage(BTService btService, String message)
	 {
	        // Check that there's actually something to send
	        if (message.length() > 0) {
	            // Get the message bytes and tell the BTService to write
	            byte[] send = message.getBytes();
	            btService.write(send);

	            //for Amarino MeetAndroid  compatible ack=19
	            byte[] ack = {(byte)19};
	            btService.write(ack);
	        }
	 }
	 
	 @Override
	  public void onSensorChanged(SensorEvent event) {
	      	Sensor mySensor = event.sensor;
	      	if (mySensor.getType() == SensorManager.SENSOR_ORIENTATION) {
	  	    		x = event.values[SensorManager.DATA_X];
	  	    		y = event.values[SensorManager.DATA_Y];
	  	    		z = event.values[SensorManager.DATA_Z];
	  	    		
	  	    		xyz_value.setText("x: " + Math.round(x) + ", y:" + Math.round(y) + ", z:" + Math.round(z));
	  	    		if(x <= -3)
	  	    		{// Forward
	  	    			if(nStatus != SENSOR_FORWARD)
	  	    			{
	  	    				nStatus = SENSOR_FORWARD;
	  	            		sendMessage(mduinobt2.mCurrentBTService, "f");
		  	    			Log.i("sensorcontrol", " Forward!");
	  	    			}
	  	    		}else if(x >= 3)
	  	    		{  // Backward
	  	    			if(nStatus != SENSOR_BACKWARD)
	  	    			{
	  	    				nStatus = SENSOR_BACKWARD;
	  	            		sendMessage(mduinobt2.mCurrentBTService, "b");
		  	    			Log.i("sensorcontrol", " Backward!");
	  	    			}
	  	    		}else if(y <= -3)
	  	    		{   // Left
	  	    			if(nStatus != SENSOR_LEFT)
	  	    			{
	  	    				nStatus = SENSOR_LEFT;
	  	            		sendMessage(mduinobt2.mCurrentBTService, "l");
		  	    			Log.i("sensorcontrol", " Left!");
	  	    			}
	  	    		}else if(y >= 3)
	  	    		{   // Right
	  	    			if(nStatus != SENSOR_RIGHT)
	  	    			{
	  	    				nStatus = SENSOR_RIGHT;
	  	            		sendMessage(mduinobt2.mCurrentBTService, "r");
		  	    			Log.i("sensorcontrol", " Right!");
	  	    			}
	  	    		}
	  	    		else
	  	    		{
	  	    			if(nStatus != SENSOR_STOP)
	  	    			{
	  	    				nStatus = SENSOR_STOP;
	  	            		sendMessage(mduinobt2.mCurrentBTService, "s");
		  	    			Log.i("sensorcontrol", " Stop!");
	  	    			}
	  	    		}
	      	    }
//	      	}        	
	 }	
	
	 @Override
	public void onResume() {
			super.onResume();
			// register this class as a listener for the orientation and
			// accelerometer sensors
			sensorMgr.registerListener(this,
					sensorMgr.getDefaultSensor(SensorManager.SENSOR_ACCELEROMETER),
					sensorMgr.SENSOR_DELAY_NORMAL);
		}

		@Override
		public void onPause() {
			super.onPause();
			// unregister listener
			sensorMgr.unregisterListener(this);
		}	

		@Override
		protected void onStop() {
			super.onStop();
			// unregister listener
			sensorMgr.unregisterListener(this);
		}

	    @Override
	    public boolean onCreateOptionsMenu(Menu menu) {
	         menu.add(0, 0, 0, "Button");
	         menu.add(0, 1, 1, "Sensor");
	         return super.onCreateOptionsMenu(menu);
	    }
		
	    @Override
	    public boolean onOptionsItemSelected(MenuItem item) {
	    	switch(item.getItemId()) {
	    	case 0:
	           // Button Control
	    			finish();
	                break;
	        case 1:
	          // Sensor Control
       		
	        		break;
	        default:
	            }
	      return super.onOptionsItemSelected(item);
	     }
	
}