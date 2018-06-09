package googleActionDemo.fulfillment;

import org.eclipse.paho.client.mqttv3.MqttClient;
import org.eclipse.paho.client.mqttv3.MqttConnectOptions;
import org.eclipse.paho.client.mqttv3.MqttException;
import org.eclipse.paho.client.mqttv3.MqttMessage;
import org.eclipse.paho.client.mqttv3.persist.MemoryPersistence;

public final class MqttConectDemo {
	
	private static MqttConectDemo mqttConectDemo = new MqttConectDemo();
	
	private MqttConectDemo () { // private constructor
		String broker       = "tcp://iot.eclipse.org:1883";
        String clientId     = "aecb83d8-8de1-4b8c-a728-943f60f9bc2c";
        MemoryPersistence persistence = new MemoryPersistence();
        
        try {
        	_sampleClient = new MqttClient(broker, clientId, persistence);
            MqttConnectOptions connOpts = new MqttConnectOptions();
            connOpts.setCleanSession(true);
            System.out.println("Connecting to broker: "+broker);
            _sampleClient.connect(connOpts);
            System.out.println("Connected");
        } catch(MqttException me) {
        	System.out.println("reason "+me.getReasonCode());
            System.out.println("msg "+me.getMessage());
            System.out.println("loc "+me.getLocalizedMessage());
            System.out.println("cause "+me.getCause());
            System.out.println("excep "+me);
            me.printStackTrace();
        }
    }
	
	private static MqttClient _sampleClient;
	
	public static MqttConectDemo getInstant() {
		return mqttConectDemo;
	} 
    
    public static void publishToMqtt(String topic, String content, int qos) {
    	MqttMessage message = new MqttMessage(content.getBytes());
        message.setQos(qos);
        
        try {
			_sampleClient.publish(topic, message);
		} catch (MqttException me) {
			System.out.println("reason "+me.getReasonCode());
            System.out.println("msg "+me.getMessage());
            System.out.println("loc "+me.getLocalizedMessage());
            System.out.println("cause "+me.getCause());
            System.out.println("excep "+me);
            me.printStackTrace();
		}
        System.out.println("Message published");
    }
}
