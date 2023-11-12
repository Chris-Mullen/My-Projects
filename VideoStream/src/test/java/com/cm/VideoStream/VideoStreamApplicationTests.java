package com.cm.VideoStream;

import org.junit.jupiter.api.Assertions;
import org.junit.jupiter.api.Test;
import org.junit.jupiter.params.ParameterizedTest;
import org.junit.jupiter.params.provider.NullAndEmptySource;
import org.junit.jupiter.params.provider.ValueSource;
import org.junit.runner.RunWith;
import org.springframework.boot.test.context.SpringBootTest;
import org.springframework.test.context.junit4.SpringRunner;

@SpringBootTest
@RunWith(SpringRunner.class)
class VideoStreamApplicationTests {
	@ParameterizedTest
	@NullAndEmptySource
	void testWelcomeDefaults(String username) {
		String expected = "Welcome Guest! <p><a href=\"sample.html\">Watch Video Stream</a></p>";
		Assertions.assertEquals(expected, VideoStreamApplication.welcome(username));
	}

	@ParameterizedTest
	@ValueSource(strings = {"user", "12345", "@$-+|}" })
	void testWelcome(String username) {
		String expected = String.format("Welcome %s! <p><a href=\"sample.html\">Watch Video Stream</a></p>", username);
		Assertions.assertEquals(expected, VideoStreamApplication.welcome(username));
	}

	@Test
	void testGetVideos() {}
}
