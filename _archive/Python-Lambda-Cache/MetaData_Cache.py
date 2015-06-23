"""
    ,':Y

    surely there is nothing that cannot be solved by caching?

"""
import time
enableMetaCache = True  # set to False to disable metadata cache
debugOutput = True


class MetadataCache(object):
    cache = {}
    cache_age = {}
    instance = None
    invalidation_time = 3600  # seconds

    def __new__(cls, *args, **kwargs):
        if not cls.instance:
            cls.instance = super(MetadataCache, cls).__new__(cls, *args, **kwargs)
        return cls.instance

    def __init__(self):
        pass

    def __setitem__(self, key, value):
        self.set(key, value)

    def __getitem__(self, key):
        return self.get(key, lambda: False)

    def __delitem__(self, key):
        self.unset(key)

    def set(self, key, value):
        if debugOutput:
            print 'warming: ', key
        self.cache[key] = value
        self.cache_age[key] = int(time.time())
        return value

    def get(self, key, default=lambda: False):
        if self.cache_age.get(key, 0) + self.invalidation_time < time.time():
            self.unset(key)
            result = False
        else:
            result = self.cache.get(key, False)
        if debugOutput:
            if result:
                print 'warm hit: ', key, ' age: ', str(time.time() - self.cache_age.get(key, 0))
            else:
                print 'cold hit: ', key
        return enableMetaCache and result or self.set(key, default())

    def unset(self, key):
        if self.cache.get(key, False):
            del self.cache[key]