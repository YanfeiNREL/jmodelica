package org.jmodelica.common.evaluation;

import java.io.BufferedWriter;
import java.io.IOException;
import java.util.LinkedHashMap;
import java.util.Map;

import org.jmodelica.common.options.AbstractOptionRegistry;

public class ExternalProcessMultiCache<K extends ExternalProcessMultiCache.Variable<V, T>, V extends ExternalProcessMultiCache.Value, T extends ExternalProcessMultiCache.Type<V>, E extends ExternalProcessMultiCache.External<K>> {

    public interface External<K> {
        public String getName();

        public int processLimit();

        public boolean dynamicEvaluatorEnabled();

        public AbstractOptionRegistry myOptions();

        public String libraryDirectory();

        public K cachedExternalObject();

        public Iterable<K> externalObjectsToSerialize();

        public Iterable<K> functionArgsToSerialize();

        public String functionArgsSerialized();

        public String functionReturnArgSerialized();

        public Iterable<K> varsToDeserialize();

        public String[] library();
    }

    public interface Variable<V extends Value, T extends Type<V>> {
        public V ceval();

        public T type();
    }

    public interface Value {
        public String getMarkedExternalObject();

        public void serialize(BufferedWriter out) throws IOException;
    }

    public interface Type<V extends Value> {
        public V deserialize(ProcessCommunicator<V, ? extends Type<V>> processCommunicator) throws IOException;
    }

    private Map<String, ExternalProcessCache<K, V, T, E>> map = new LinkedHashMap<>();

    private ExternalFunctionCompiler<K, E> mc;

    public ExternalProcessMultiCache(ExternalFunctionCompiler<K, E> mc) {
        this.mc = mc;
    }

    public ExternalProcessCache<K, V, T, E> getExternalProcessCache(String key) {
        ExternalProcessCache<K, V, T, E> ce = map.get(key);
        if (ce == null) {
            ce = createCachedExternals();
            map.put(key, ce);
        }
        return ce;
    }
    
    public ExternalProcessCache<K, V, T, E> createCachedExternals() {
        return new ExternalProcessCacheImpl<K, V, T, E>(mc);
    }

    public void destroyProcesses() {
        for (ExternalProcessCache<K, V, T, E> ce : map.values()) {
            ce.destroyProcesses();
        }
    }

    public void tearDown() {
        for (ExternalProcessCache<K, V, T, E> ce : map.values()) {
            ce.tearDown();
        }
        map.clear();
    }

    public void tearDown(String key) {
        ExternalProcessCache<K, V, T, E> ce = map.remove(key);
        if (ce != null) {
            ce.tearDown();
        }
    }

}
