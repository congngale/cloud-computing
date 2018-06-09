package googleActionDemo.fulfillment;

import org.springframework.boot.SpringApplication;
import org.springframework.boot.autoconfigure.SpringBootApplication;
import org.springframework.web.bind.annotation.*;

@SpringBootApplication
@RestController
public class FulfillmentApplication {
	public static void main(String[] args) {
        SpringApplication.run(FulfillmentApplication.class, args);
	}
	
	@GetMapping("/")
    public String hello() {
            return "Hello Spring Boot!";
    }
}