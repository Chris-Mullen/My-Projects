package com.cm.VideoStream;

import org.junit.jupiter.api.Assertions;
import org.junit.jupiter.api.Test;
import org.junit.jupiter.params.ParameterizedTest;
import org.junit.jupiter.params.provider.NullAndEmptySource;
import org.junit.jupiter.params.provider.ValueSource;
import org.springframework.boot.test.context.SpringBootTest;

@SpringBootTest
class VideoStreamApplicationTests {

	@Test
	void contextLoads() {
	}

	@ParameterizedTest
	@NullAndEmptySource
	void testWelcomeDefaults(String _username) {
		String expected = "Welcome Guest!";
		Assertions.assertEquals(expected, VideoStreamApplication.sayHello(_username));
	}

	@ParameterizedTest
	@ValueSource(strings = {"user", "12345", "@$-+|}" })
	void testSayHello(String username) {
		String expected = "Welcome " + username + "!";
		Assertions.assertEquals(expected, VideoStreamApplication.sayHello(username));
	}
}
