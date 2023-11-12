package com.cm.VideoStream;

import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.boot.SpringApplication;
import org.springframework.boot.autoconfigure.SpringBootApplication;
import org.springframework.core.io.Resource;
import org.springframework.web.bind.annotation.*;
import reactor.core.publisher.Mono;

@SpringBootApplication
@RestController
public class VideoStreamApplication {
	public static final String DEFAULT_USER = "Guest";
	public static final String SAMPLE="classpath:videos/sample.mp4";
	public static final String SAMPLE2="classpath:videos/sample2.mp4";

	@Autowired
	private StreamingService service;

	public static void main(String[] args) { SpringApplication.run(VideoStreamApplication.class, args); }

	/*
	 * Display a Welcome Message to the user
	 * query parameters:
	 * username, default: "Guest"
	 *
	 * Chris Mullen 2023
	 */
	@GetMapping("")
	public static String welcome(@RequestParam(value = "username", required = false, defaultValue = DEFAULT_USER) String name) {
		if(name == null || name.trim().isEmpty()) { name = DEFAULT_USER; }
		return String.format("Welcome %s! <p><a href=\"sample.html\">Watch Video Stream</a></p>", name);
	}

	/*
	 * Display Sample Video Stream to the user
	 *
	 * Chris Mullen 2023
	 */
	@GetMapping(value = "video/{title}", produces = "video/mp4")
	public Mono<Resource> getVideos(@RequestHeader("Range") String range){
		System.out.println("range (bytes): " + range);

		return service.getVideo(SAMPLE);
	}
}
