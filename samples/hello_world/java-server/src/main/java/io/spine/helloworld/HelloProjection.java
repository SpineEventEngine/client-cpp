package io.spine.helloworld;

import io.spine.core.Subscribe;
import io.spine.server.aggregate.Apply;
import io.spine.server.command.Assign;
import io.spine.server.projection.Projection;

public class HelloProjection extends Projection<HelloId, LastHello, LastHelloVBuilder>
{
    /**
     * Creates a new instance.
     *
     * @param id the ID for the new instance
     * @throws IllegalArgumentException if the ID is not of one of the supported types
     */
    protected HelloProjection(HelloId id) {
        super(id);
    }

    @Subscribe
    void on(HelloReceived ev) {
        getBuilder().setUsername(ev.getUsername());
    }
}
