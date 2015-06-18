Code Sample (Python)

Python-Lambda-Cache
===================

Cache interface in Python, deferred evaluation with lambdas, can be plugged onto e.g. redis

    md_device = MetadataCache()
    
    def get_an_item:
      item = md_device.get('cachekey.name', lambda: your_database.get(an_item))
      
    get_an_item()  # returns item, also warms cache
    get_an_item()  # returns cached item
    
    
    
