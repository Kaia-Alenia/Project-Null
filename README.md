# 🚀 Azulito: El Juego de Cuadrados Mágicos 🚀
[![Build Status](https://img.shields.io/badge/Build-Passing-green.svg)](https://github.com/)
[![License](https://img.shields.io/badge/License-MIT-blue.svg)](https://github.com/)

## 📚 Descripción
Azulito es un juego/demo simple para la consola Game Boy Advance (GBA) que permite controlar un cuadrado azul en la pantalla utilizando las teclas de dirección. El cuadrado puede cambiar de color a rojo o verde presionando las teclas A o B, respectivamente.

## 🗂️ Estructura
El proyecto consta de un archivo principal `src/main.c` que contiene el código fuente del juego. Este archivo se encarga de configurar la pantalla, leer los controles, actualizar la posición y el color del cuadrado, y dibujar todo en la pantalla.

## 🛠️ Compilación
El proyecto utiliza un Makefile para compilar el código fuente y crear un archivo ejecutable para la GBA. Para compilar el proyecto, es necesario tener instalado DevKitPro, una suite de herramientas de desarrollo para la GBA. Simplemente ejecute `make` en la terminal para compilar el proyecto.

## 📝 Notas
* El juego utiliza un algoritmo de fuerza bruta para borrar la pantalla y dibujar el cuadrado, lo que puede causar un ligero parpadeo.
* El juego no tiene un objetivo específico, solo es un demo para mostrar cómo controlar un objeto en la pantalla y cambiar su color.

## 📚 Recursos
* [DevKitPro](https://devkitpro.org/): Suite de herramientas de desarrollo para la GBA.
* [GBA Documentation](https://github.com/gbdev/wiki): Documentación oficial de la GBA.

## 🤝 Contribuir
Si deseas contribuir al proyecto, por favor, crea un fork del repositorio y envía una solicitud de pull request con tus cambios. Asegúrate de seguir las reglas de contribución y de que tus cambios sean compatibles con la licencia del proyecto. 🙏