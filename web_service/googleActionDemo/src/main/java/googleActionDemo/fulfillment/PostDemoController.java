package googleActionDemo.fulfillment;

import org.springframework.stereotype.Controller;
import org.springframework.web.bind.annotation.ModelAttribute;
import org.springframework.web.bind.annotation.PostMapping;

import Model.Greeting;

@Controller
public class PostDemoController {

	@PostMapping("/postdemo")
    public String greetingSubmit(@ModelAttribute Greeting greeting) {
        return "result";
    }
}
