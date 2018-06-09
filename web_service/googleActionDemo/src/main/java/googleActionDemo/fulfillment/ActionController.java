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

		Map<String, Object> queryResult = (Map<String, Object>) request.get("queryResult");
		String action = queryResult.get("action").toString();
		Map<String, Object> parameters = (Map<String, Object>) queryResult.get("parameters");
		
		String changeValue = "0";
		if (parameters.get("change-value") != null) {
			changeValue = parameters.get("change-value").toString();
		}
		
		String color = "";
		if (parameters.get("color") != null) {
			color = parameters.get("color").toString();
		}
		
		int value = (int) Double.parseDouble(changeValue);
		value = (int) ((value * 255)/100);
		
		HashMap<String, String> map = new HashMap<>();
	    map.put("fulfillmentText", "Okay");
	    
	    String topic        = "";
        String content      = "";
        int qos             = 1;
        
	    switch (action) {
		case "smarthome.lights.switch.on":
			content = "{\"cmd\":\"on\"}";
			topic = "homa/control";
			break;
			
		case "smarthome.lights.switch.off":
			content = "{\"cmd\":\"off\"}";
			topic = "homa/control";
			break;
		
		case "smarthome.lights.brightness.down":
			content = "{\"cmd\":\"warm\",\"value\":"+value+"}";
			topic = "homa/control";
			break;
		
		case "smarthome.lights.brightness.up":
			content = "{\"cmd\":\"warm\",\"value\":"+value+"}";
			topic = "homa/control";
			break;
			
		case "smarthome.lights.switch.color":
			
			if(color.equals("red"))
				content = "{\"cmd\":\"rgb\",\"red\":255,\"green\":0,\"blue\":0}";
			else if(color.equals("green"))
				content = "{\"cmd\":\"rgb\",\"red\":0,\"green\":255,\"blue\":0}";
			else if(color.equals("blue"))
				content = "{\"cmd\":\"rgb\",\"red\":0,\"green\":0,\"blue\":255}";
			else 
				content = "{\"cmd\":\"rgb\",\"red\":255,\"green\":255,\"blue\":255}";
			
			topic = "homa/control";
			break;	

		default:
			break;
		}
	    
	    MqttConectDemo.publishToMqtt(topic, content, qos);
	    return map;
    }
}
