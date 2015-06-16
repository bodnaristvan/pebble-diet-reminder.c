all:
	pebble build

clean:
	pebble clean

install:
	@if test -z "$$PEBBLE_PHONE"; then \
		echo "Please set the PEBBLE_PHONE shell var to the IP of your development phone"; \
	else \
		pebble install --phone $$PEBBLE_PHONE --logs; \
	fi;
