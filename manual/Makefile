# 
all: html

confcheck:
	@if test "x$(PHPDOC)" = "x"; then echo PHPDOC not set; exit 3; fi

manual.xml: manual.xml.in
	sed -e's:@PHPDOC@:$(PHPDOC):g' < manual.xml.in > manual.xml

html: confcheck manual.xml
	rm -rf html; mkdir html
	SP_ENCODING=XML SP_CHARSET_FIXED=YES openjade -D $(PHPDOC) -wno-idref -c $(PHPDOC)/entities/ISO/catalog -c $(PHPDOC)/dsssl/docbook/catalog -c $(PHPDOC)/dsssl/defaults/catalog -d $(PHPDOC)/dsssl/html.dsl -V use-output-dir -t sgml $(PHPDOC)/dtds/dbxml-4.1.2/phpdocxml.dcl manual.xml

tex: manual.tex

manual.tex: confcheck manual.xml
	SP_ENCODING=XML SP_CHARSET_FIXED=YES /usr/bin/openjade -D $(PHPDOC) -wno-idref -c $(PHPDOC)/entities/ISO/catalog -c $(PHPDOC)/dsssl/docbook/catalog -c $(PHPDOC)/dsssl/defaults/catalog -d $(PHPDOC)/dsssl/print.dsl -t tex $(PHPDOC)/dtds/dbxml-4.1.2/phpdocxml.dcl manual.xml

pdf: manual.tex
	pdfjadetex manual.tex && pdfjadetex manual.tex && pdfjadetex manual.tex
