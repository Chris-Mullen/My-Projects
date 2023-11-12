package com.cm.VideoStream;

import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.core.io.Resource;
import org.springframework.core.io.ResourceLoader;
import org.springframework.stereotype.Service;
import reactor.core.publisher.Mono;

@Service
public class StreamingService {
    @Autowired
    private ResourceLoader resourceLoader;
    public Mono<Resource> getVideo(String path){ return Mono.fromSupplier(() -> resourceLoader.getResource(path)); }
}
