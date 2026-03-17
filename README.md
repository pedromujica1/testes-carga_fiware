# TESTES DE CARGA FIWARE

#execução nova
#100 rps
./jmeter -n -t FiwareInputMQTT.jmx -l relatorio100.jtl -e -o relatorio100 -Jtarget_rpm=6000

#200 rps
./jmeter -n -t FiwareInputMQTT.jmx -l relatorio200.jtl -e -o relatorio200 -Jtarget_rpm=12000

#300 rps
./jmeter -n -t FiwareInputMQTT.jmx -l relatorio300.jtl -e -o relatorio300 -Jtarget_rpm=18000

#400 rps
./jmeter -n -t FiwareInputMQTT.jmx -l relatorio400.jtl -e -o relatorio400 -Jtarget_rpm=24000

#500 rps
./jmeter -n -t FiwareInputMQTT.jmx -l relatorio500.jtl -e -o relatorio500 -Jtarget_rpm=30000

#1000rps
./jmeter -n -t FiwareInputMQTT.jmx -l relatorio1000.jtl -e -o relatorio1000 -Jtarget_rpm=60000
