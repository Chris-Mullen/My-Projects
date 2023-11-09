package com.cm.VideoStream;

import org.springframework.boot.SpringApplication;
import org.springframework.boot.autoconfigure.SpringBootApplication;
import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.RequestParam;
import org.springframework.web.bind.annotation.RestController;

@SpringBootApplication
@RestController
public class VideoStreamApplication {
	public static final String DEFAULT_USER = "Guest";

	public static void main(String[] args) { SpringApplication.run(VideoStreamApplication.class, args); }

	/*
	 * Display a Welcome Message to the user
	 * query parameters:
	 * username, default: "Guest"
	 * Chris Mullen 2023
	 */
	@GetMapping("")
	public static String sayHello(@RequestParam(value = "username", required = false, defaultValue = DEFAULT_USER) String name) {
		if(name == null || name.trim().isEmpty()) { name = DEFAULT_USER; }
		return String.format("Welcome %s!", name);
	}
}
