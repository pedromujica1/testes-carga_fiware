# grafos-caminhos-minimos
int c = (vars.get("counter") ?: "0") as int
c++
vars.put("counter", c.toString())


import java.util.*
import java.nio.ByteBuffer
import java.util.Base64

def random = new Random()

def payload = new ByteArrayOutputStream()

// Campo A - Pressão
float pressure = 980 + random.nextFloat() * (1030 - 980)
int pressureLpp = (int)(pressure * 10)
payload.write([0x00, 0x73] as byte[])
payload.write(ByteBuffer.allocate(2).putShort((short)pressureLpp).array())

// Campo B - Temperatura
float temp = 20 + random.nextFloat() * (35 - 20)
int tempLpp = (int)(temp * 10)
payload.write([0x01, 0x67] as byte[])
payload.write(ByteBuffer.allocate(2).putShort((short)tempLpp).array())

// Campo C - Umidade
float humidity = 30 + random.nextFloat() * (80 - 30)
int humidityLpp = (int)(humidity * 2)
payload.write([0x02, 0x68] as byte[])
payload.write((byte)humidityLpp)

// Campo D fixo
payload.write([0x03, 0x00, 0x64] as byte[])

// Campo E fixo
payload.write([0x04, 0x01, 0x00] as byte[])

// Campo F fixo
payload.write([0x05, 0x01, 0xD7] as byte[])

def encoded = Base64.encoder.encodeToString(payload.toByteArray())

vars.put("payload_raw", encoded)
vars.put("dev_id", "myDevice${ctx.getThreadNum()}")
vars.put("counter", vars.get("counter") ?: "0")
