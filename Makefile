
rendu: normalize archive

normalize: 
	astyle -A8 -s4 --suffix=none --recursive '*.cpp' '*.hpp'

archive:
	@echo "====================================================="
	@echo "           MERCI DE CONTROLER LE CONTENU CI-DESSOUS  "
	@echo "              PLEASE CHECK THE CONTENT BELOW         "
	@echo "====================================================="
	@zip -r scorpion-${GROUPE}.zip SCIPER* JOURNAL* README* REPONSES* \
	partie*/src partie*/extlib partie*/res partie*/SConstruct \
	-x '*/gmon.out' -x '*/*~' -x '*/.svn/*' -x '*/core' -x '*/*.zip'\
	-x '*/*.orig' -x '*/.git/*' -x '*/build/*' -x '*/*.o'
	@echo "L'ARCHIVE scorpion-${GROUPE}.zip EST CONSTRUITE"
	@echo "MERCI DE LA CONTROLER AVANT DE LA SOUMETTRE SUR MOODLE"
	@du -h scorpion-${GROUPE}.zip
