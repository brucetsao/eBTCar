/*
 * Remote-control car by Bluetooth
 * Author: http://motoduino.com
 * Date: Feb. 2012
 */


package com.motoduino.mduinobt2;

import android.app.Activity;
import android.bluetooth.BluetoothAdapter;
import android.bluetooth.BluetoothDevice;
import android.content.Intent;
import android.content.pm.ActivityInfo;
import android.os.Bundle;
import android.os.Handler;
import android.os.Message;
import android.util.Log;
import android.view.Menu;
import android.view.MenuInflater;
import android.view.MenuItem;
import android.view.MotionEvent;
import android.view.View;
import android.view.View.OnTouchListener;
import android.widget.ImageButton;
import android.widget.RelativeLayout;
import android.widget.Toast;

public class mduinobt2 extends Activity {

	private static final String TAG = "mduinobt2";
    private static final boolean D = true;
//    public static String bluetooth_address;
//  Modify DEVICE_ADDRESS for your bluetooth    
	private static final String DEVICE_ADDRESS = "00:11:11:04:09:90";  //Bluetooth Address
    public static final String DEVICE_NAME = "device_name";
    public static final String TOAST = "toast";
	ImageButton button_left, button_right, button_forward, button_back;

    // Message types sent from the BluetoothChatService Handler
    public static final int MESSAGE_STATE_CHANGE = 1;
    public static final int MESSAGE_READ = 2;
    public static final int MESSAGE_WRITE = 3;
    public static final int MESSAGE_DEVICE_NAME = 4;
    public static final int MESSAGE_TOAST = 5;
    
    // Intent request codes
    private static final int REQUEST_CONNECT_DEVICE = 1;
    private static final int REQUEST_ENABLE_BT = 2;
    private RelativeLayout btnControlLayout;

    private static Intent myIntent;
    
    // Name of the connected device
    private String mConnectedDeviceName_1 = null;
    private BluetoothAdapter mBluetoothAdapter = null;
    // Member object for the bluetooth services
    private BTService mBTService_1 = null;
    public static BTService mCurrentBTService = null;
    ImageButton btn_BTDiscovery;    
	final int DELAY = 150;    
	 
    @Override
    public void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);

        if(D) Log.e(TAG, "+++ ON CREATE +++");

        setContentView(R.layout.main);
        setRequestedOrientation (ActivityInfo.SCREEN_ORIENTATION_PORTRAIT);        

        // my button control
        button_forward = (ImageButton)findViewById(R.id.forward); 
        button_back = (ImageButton)findViewById(R.id.backward); 
        button_left = (ImageButton)findViewById(R.id.left); 
        button_right = (ImageButton)findViewById(R.id.right); 

        button_forward.setOnTouchListener(new OnTouchListener() {
            @Override
            public boolean onTouch(View v, MotionEvent event) {
                if ( event.getAction() == MotionEvent.ACTION_UP ) {
                    
                    Log.i(TAG, "FORWARD BUTTON UP =" + event.getAction() );
            		sendMessage(mBTService_1, "s");
                }
                else if( event.getAction() == MotionEvent.ACTION_DOWN)
                {
                    Log.i(TAG, "FORWARD BUTTON DOWN ="+ event.getAction());
            		sendMessage(mBTService_1, "f");
                }
                	return true;

            }
        });        

        button_back.setOnTouchListener(new OnTouchListener() {
            @Override
            public boolean onTouch(View v, MotionEvent event) {
                if ( event.getAction() == MotionEvent.ACTION_UP ) {
                    
                    Log.i(TAG, "BACK BUTTON UP =" + event.getAction() );
            		sendMessage(mBTService_1, "s");
                }
                else if( event.getAction() == MotionEvent.ACTION_DOWN)
                {
                    Log.i(TAG, "BACK BUTTON DOWN ="+ event.getAction());
            		sendMessage(mBTService_1, "b");
                }
               	return true;

            }
        });        

        button_left.setOnTouchListener(new OnTouchListener() {
            @Override
            public boolean onTouch(View v, MotionEvent event) {
                if ( event.getAction() == MotionEvent.ACTION_UP ) {
                    
                    Log.i(TAG, "LEFT BUTTON UP =" + event.getAction() );
            		sendMessage(mBTService_1, "s");
                }
                else if( event.getAction() == MotionEvent.ACTION_DOWN)
                {
                    Log.i(TAG, "LEFT BUTTON DOWN ="+ event.getAction());
            		sendMessage(mBTService_1, "l");
                }
               	return true;
            }
        });        
        
        button_right.setOnTouchListener(new OnTouchListener() {
            @Override
            public boolean onTouch(View v, MotionEvent event) {
                if ( event.getAction() == MotionEvent.ACTION_UP ) {
                    
                    Log.i(TAG, "RIGHT BUTTON UP =" + event.getAction());
            		sendMessage(mBTService_1, "s");
                }
                else if( event.getAction() == MotionEvent.ACTION_DOWN)
                {
                    Log.i(TAG, "RIGHT BUTTON DOWN =" + event.getAction());
            		sendMessage(mBTService_1, "r");
                }
                return true;
            }
        });        

        // Get local Bluetooth adapter
        mBluetoothAdapter = BluetoothAdapter.getDefaultAdapter();

        // If the adapter is null, then Bluetooth is not supported
        if (mBluetoothAdapter == null) {
            Toast.makeText(this, "Bluetooth is not available", Toast.LENGTH_LONG).show();
            finish();
            return;
        }
        
        // If BT is not on, request that it be enabled.
        if (!mBluetoothAdapter.isEnabled()) {
            if(D) Log.e(TAG, "startActivityForResult: REQUEST_ENABLE_BT");
        	
            Intent enableIntent = new Intent(BluetoothAdapter.ACTION_REQUEST_ENABLE);
            startActivityForResult(enableIntent, REQUEST_ENABLE_BT);
        } else {
            mBTService_1 = new BTService(this, mHandler);
        }
        
    }
        
        
    @Override
    public void onStart() {
        super.onStart();
        if(D) Log.e(TAG, "++ ON START ++");
     
    }
    
	@Override
	protected void onStop() {
		super.onStop();
		
	}

	@Override
	protected void onDestroy() {
		super.onDestroy();
		
        if (mBTService_1 != null) mBTService_1.stop();
        if(D) Log.e(TAG, "--- ON DESTROY ---");

	}

    @Override
    public synchronized void onResume() {
        super.onResume();
        if(D) Log.e(TAG, "+ ON RESUME +");

        // Performing this check in onResume() covers the case in which BT was
        // not enabled during onStart(), so we were paused to enable it...
        // onResume() will be called when ACTION_REQUEST_ENABLE activity returns.
        if (mBTService_1 != null) {
            // Only if the state is STATE_NONE, do we know that we haven't started already
            if (mBTService_1.getState() == BTService.STATE_NONE) {
              // Start the Bluetooth chat services
              mBTService_1.start();
            }
        }
        
    }

    @Override
    public synchronized void onPause() {
        super.onPause();
        if(D) Log.e(TAG, "- ON PAUSE -");
    }
    
    private boolean checkDeviceConnection()
    {
    	if((mCurrentBTService == null) || (mCurrentBTService.getState() != BTService.STATE_CONNECTED))
    	{
            Toast.makeText(this, R.string.title_not_connected, Toast.LENGTH_SHORT).show();
            return false;
    	}
    	return true;
    	
    }
    /**
     * Sends a message.
     * @param message  A string of text to send.
     */
    private void sendMessage(BTService btService, String message) {
        // Check that we're actually connected before trying anything
    	if (!checkDeviceConnection())
    		return;

        // Check that there's actually something to send
        if (message.length() > 0) {
            // Get the message bytes and tell the BTService to write
        	
            byte[] send = message.getBytes();
            
            btService.write(send);
            
        	//for Amarino MeetAndroid  compatible ack=19
            byte[] ack = {(byte)19};
            btService.write(ack);
            // Reset out string buffer to zero and clear the edit text field
        }
    }
	
    // The Handler that gets information back from the BluetoothChatService
    private final Handler mHandler = new Handler() {
        @Override
        public void handleMessage(Message msg) {
            switch (msg.what) {
            case MESSAGE_STATE_CHANGE:
                if(D) Log.i(TAG, "MESSAGE_STATE_CHANGE: " + msg.arg1);
                switch (msg.arg1) {
                case BTService.STATE_CONNECTED:
                    	if(D) Log.d(TAG, " Set Car 1 active!");
                    	btnControlLayout = (RelativeLayout)findViewById(R.id.btncontrol);
                    	btnControlLayout.setBackgroundColor(android.graphics.Color.RED);
            	
                     break;
                case BTService.STATE_CONNECTING:
                    Toast.makeText(getApplicationContext(), " Device is connecting! ", Toast.LENGTH_SHORT).show();
                    break;
                case BTService.STATE_LISTEN:
                		break;
                case BTService.STATE_NONE:
//                    Toast.makeText(getApplicationContext(), " Devices disconnected ! ", Toast.LENGTH_SHORT).show();
                	break;
                }
                break; 
            case MESSAGE_WRITE:
                break;
            case MESSAGE_READ:
            	break;
            case MESSAGE_DEVICE_NAME:
	                // save the connected device's name
	                mConnectedDeviceName_1 = msg.getData().getString(DEVICE_NAME);
	                Toast.makeText(getApplicationContext(), "Connected to "
	                               + mConnectedDeviceName_1, Toast.LENGTH_SHORT).show();
         	  break;
            case MESSAGE_TOAST:
                if(D) Log.d(TAG, "MESSAGE_TOAST !");
            	if(msg.getData().getString(TOAST) == null)
            		break;
                Toast.makeText(getApplicationContext(), msg.getData().getString(TOAST),
                               Toast.LENGTH_SHORT).show();
                break;
            }
        }
    };
    
    public void onRestoreInstanceState(Bundle savedInstanceState)
    {
        if(D) Log.d(TAG, "onRestoreInstanceState!");
    	
    }

    public void onSaveInstanceState(Bundle savedInstanceState)
    {
        if(D) Log.d(TAG, "onSaveInstanceState!");
    	
    }
    
    @Override
    public boolean onCreateOptionsMenu(Menu menu) {
        MenuInflater inflater = getMenuInflater();
        inflater.inflate(R.menu.option_menu, menu);
        return true;
    }

    @Override
    public boolean onOptionsItemSelected(MenuItem item) {
        switch (item.getItemId()) {
        case R.id.connect:
            Log.i(TAG, "Connect Device"+DEVICE_ADDRESS);
            // Get local Bluetooth adapter
            mBluetoothAdapter = BluetoothAdapter.getDefaultAdapter();

            // If the adapter is null, then Bluetooth is not supported
            if (mBluetoothAdapter == null) {
                Toast.makeText(mduinobt2.this, "Bluetooth is not available", Toast.LENGTH_LONG).show();
                return true;
            }
            
            // If BT is not on, request that it be enabled.
            if (!mBluetoothAdapter.isEnabled()) {
                if(D) Log.e(TAG, "startActivityForResult: REQUEST_ENABLE_BT");
            	
                Intent enableIntent = new Intent(BluetoothAdapter.ACTION_REQUEST_ENABLE);
                startActivityForResult(enableIntent, REQUEST_ENABLE_BT);
                return true;
            }
            mBTService_1 = new BTService(mduinobt2.this, mHandler);
            BluetoothDevice device = mBluetoothAdapter.getRemoteDevice(DEVICE_ADDRESS);
            // Attempt to connect to the device
            mCurrentBTService =  mBTService_1;   
        	mCurrentBTService.connect(device);
            return true;
        case R.id.sensor:
            // Sensor Control
        	if (!checkDeviceConnection())
        		return true;
        	myIntent = new Intent(mduinobt2.this, sensorcontrol.class);
        	myIntent.putExtra("bluetooth_MAC", DEVICE_ADDRESS);
        	this.startActivity(myIntent);
             if(D) Log.d(TAG, "SensorControl Exit!");
            return true;
        case R.id.About:
            // About author
            Toast.makeText(this, R.string.motoduino_about, Toast.LENGTH_LONG).show();
            return true;
        case R.id.Exit:
            // Sensor Control
        	finish();
        	return true;
        }
        return false;
    }
    

}
