package googleActionDemo.fulfillment;

import java.util.HashMap;
import java.util.Map;

import org.eclipse.paho.client.mqttv3.MqttClient;
import org.eclipse.paho.client.mqttv3.MqttConnectOptions;
import org.eclipse.paho.client.mqttv3.MqttException;
import org.eclipse.paho.client.mqttv3.MqttMessage;
import org.eclipse.paho.client.mqttv3.persist.MemoryPersistence;
import org.springframework.stereotype.Controller;
import org.springframework.web.bind.annotation.PostMapping;
import org.springframework.web.bind.annotation.RequestBody;
import org.springframework.web.bind.annotation.ResponseBody;

@Controller
public class ActionController {

	@PostMapping("/action")
	@ResponseBody
    public Map<String, String> action(@RequestBody Map<String, Object> request) {
		//String responseId = request.get("responseId").toString();
		Map<String, Object> queryResult = (Map<String, Object>) request.get("queryResult");
		String queryText = queryResult.get("queryText").toString();
		HashMap<String, String> map = new HashMap<>();
	    map.put("fulfillmentText", queryText);
	    
	    String topic        = "MQTT Examples";
        String content      = "Message from MqttPublishSample";
        int qos             = 2;
	    publishToMqtt(topic, content, qos);

	    return map;
    }
	
	private void publishToMqtt(String topic,String content, int qos) {
		String broker       = "tcp://iot.eclipse.org:1883";
        String clientId     = "JavaSample";
        MemoryPersistence persistence = new MemoryPersistence();
        
		try {
            MqttClient sampleClient = new MqttClient(broker, clientId, persistence);
            MqttConnectOptions connOpts = new MqttConnectOptions();
            connOpts.setCleanSession(true);
            System.out.println("Connecting to broker: "+broker);
            sampleClient.connect(connOpts);
            System.out.println("Connected");
            System.out.println("Publishing message: "+content);
            MqttMessage message = new MqttMessage(content.getBytes());
            message.setQos(qos);
            sampleClient.publish(topic, message);
            System.out.println("Message published");
            sampleClient.disconnect();
            System.out.println("Disconnected");
            //System.exit(0);
        } catch(MqttException me) {
            System.out.println("reason "+me.getReasonCode());
            System.out.println("msg "+me.getMessage());
            System.out.println("loc "+me.getLocalizedMessage());
            System.out.println("cause "+me.getCause());
            System.out.println("excep "+me);
            me.printStackTrace();
        }
	}
}
