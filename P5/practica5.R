# ==========================================
# PRACTICA 5 - SONIDO EN R
# Miguel Moreno Murcia
# ==========================================

library(tuneR)
library(seewave)

# ==========================================
# 1. LEER LOS ARCHIVOS DE SONIDO
# ==========================================

nombre <- readWave("nombre.wav")
apellido <- readWave("apellido.wav")

# ==========================================
# 2. DIBUJAR FORMAS DE ONDA
# ==========================================

png("onda_nombre.png")
plot(nombre, main = "Forma de onda - Nombre")
dev.off()

png("onda_apellido.png")
plot(apellido, main = "Forma de onda - Apellido")
dev.off()

# ==========================================
# 3. INFORMACION DE LAS CABECERAS
# ==========================================

cat("\n========== INFORMACION NOMBRE ==========\n")
str(nombre)

cat("\n========== INFORMACION APELLIDO ==========\n")
str(apellido)

# ==========================================
# 4. UNIR AMBOS SONIDOS
# ==========================================

completo <- pastew(nombre, apellido)

# ==========================================
# 5. MOSTRAR Y REPRODUCIR RESULTADO
# ==========================================

png("onda_completa.png")
plot(completo, main = "Nombre y apellido")
dev.off()

plot(completo, main = "Nombre y apellido")

listen(completo)

# ==========================================
# 6. GUARDAR SONIDO BASICO
# ==========================================

writeWave(completo, "basico.wav")


# ==========================================
# FINAL
# ==========================================

cat("\nPractica finalizada correctamente.\n")