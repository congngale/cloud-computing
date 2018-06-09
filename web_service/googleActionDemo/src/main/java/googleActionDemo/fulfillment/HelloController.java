package googleActionDemo.fulfillment;

import org.springframework.stereotype.Controller;
import org.springframework.ui.Model;
import org.springframework.web.bind.annotation.GetMapping;

import Model.Greeting;

@Controller
public class HelloController {
	@GetMapping("/hello")
	public String greetingForm(Model model) {
        model.addAttribute("greeting", new Greeting());
        return "hello";
    }
}
