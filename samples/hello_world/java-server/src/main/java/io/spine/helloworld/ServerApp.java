package io.spine.helloworld;/*
 *
 * Copyright 2016, TeamDev Ltd. All rights reserved.
 *
 * Redistribution and use in source and/or binary forms, with or without
 * modification, must retain the above copyright notice and the following
 * disclaimer.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 * A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 * OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 */

import io.spine.core.BoundedContextName;
import io.spine.server.BoundedContext;
import io.spine.server.CommandService;
import io.spine.server.QueryService;
import io.spine.server.storage.StorageFactory;
import io.spine.server.storage.memory.InMemoryStorageFactory;
import io.spine.server.transport.GrpcContainer;
import org.slf4j.Logger;
import org.slf4j.LoggerFactory;

import java.io.IOException;

import static com.google.common.base.Suppliers.ofInstance;
import static io.spine.server.BoundedContext.newName;

/**
 * A template of a server application, powered by Spine.
 *
 * <p>Creates an instance of a sample bounded context and exposes it via gRPC services.
 *
 * <p>Also uses a simple gRPC client to connect to the server-side and illustrate the workflow.
 *
 * @author Alex Tymchenko
 */
public class ServerApp {

    /**
     * A name of the bounded context.
     */
    private static final BoundedContextName BOUNDED_CONTEXT_NAME = newName("Tasks");

    /**
     * A flag determining whether the server application allows multiple tenants.
     */
    private static final boolean MULTITENANT = false;

    /**
     * A host to use for gRPC server.
     */
    private static final String HOST = "127.0.0.1";

    /**
     * A port to use for gRPC server.
     */
    private static final int PORT = 8484;

    /**
     * This class must not be instantiated, as it's just a holder for {@code main} method.
     */
    private ServerApp() {}

    /**
     * Creates and starts a gRPC server and serves `Tasks` bounded context.
     *
     * <p>Uses the hard-coded {@linkplain #HOST host} and {@linkplain #PORT port} for simplicity.
     *
     * @throws IOException if gRPC server cannot be started
     */
    public static void main(String[] args) throws IOException {

        // Define a storage factory.
        final StorageFactory storageFactory =
                InMemoryStorageFactory.newInstance(BOUNDED_CONTEXT_NAME, MULTITENANT);

        final BoundedContext boundedContext =
                BoundedContext.newBuilder()
                              .setStorageFactorySupplier(ofInstance(storageFactory))
                              .setName(BOUNDED_CONTEXT_NAME.getValue())
                              .build();
        final HelloRepository repository = new HelloRepository();
        final LastHelloRepository projectionRepository = new LastHelloRepository();
        boundedContext.register(repository);
        boundedContext.register(projectionRepository);

        /*
         * Instantiate gRPC services provided by Spine
         * and configure them for the given {@code BoundedContext}.
         */
        final CommandService commandService = CommandService.newBuilder()
                                                            .add(boundedContext)
                                                            .build();
        final QueryService queryService = QueryService.newBuilder()
                                                      .add(boundedContext)
                                                      .build();

        /*
         * Deploy the services to the gRPC container.
         */
        final GrpcContainer container = GrpcContainer.newBuilder()
                                                     .setPort(PORT)
                                                     .addService(commandService)
                                                     .addService(queryService)
                                                     .build();
        container.start();
        log().info("gRPC server started at {}:{}.", HOST, PORT);

        container.awaitTermination();
    }

    /**
     * A singleton logger to use in scope of this application.
     */
    private enum LogSingleton {
        INSTANCE;

        @SuppressWarnings("NonSerializableFieldInSerializableClass")
        private final Logger value = LoggerFactory.getLogger(ServerApp.class);
    }

    private static Logger log() {
        return LogSingleton.INSTANCE.value;
    }
}
