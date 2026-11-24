# A2
1. Meet before the lab demo: Monday 12-1pm
 //will add more meeting times when we see fit

2. Work distribution:
----SAM----
-readinv

By Thursday
-open the .bin and read the header.
-helper file that contains helper functions
	-error checking file (bytes written to correct places)
	-check the header [invp,version,flag,record count]

By Saturday
  -read records into dynamic array with realloc
  -helper function for record parsing
  	-timemstamp, event, byte, qty, sku, note
By Sunday
	-build and format report


----Ben----
-packinv

By Thursday

- fgets reader for lines
- tokenize fields
- check formats of fields
- error checks 

By Saturday

- write header element of LL
 - file type
 - version
 - record count
	- record count counter implimentation
 - version flag
- Create New Node in LL

By Sunday

- fill in struct of LL element
 - timestamp
 - event byte
	- event type
	- flag for review
	- run-length marker
 	- reserved
		-check if corrupted
	- check for errors
 - quantity
 - SKU len
	- get len
 - SKU
 - Note len
	- get len
 - Note

To Work on after Demo (Expected completion Date is Saturday, Dec 5)

- write LL to binary
- impliment run length marker (-c)
- 
