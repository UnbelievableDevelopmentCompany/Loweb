# Веб-backend-фреймворк Loweb.
## О фреймворке
Фреймворк написан на C++.
Он реализует паттерн MTV.
Loweb чем-то схож с фреймворком Django, но только для C++.
## Основы
Сначала нужно создать класс, унаследованный от `Loweb::ProjectConfig`.
В конструкторе можно указать файл конфигурации при помощи метода Config. Например:Config("config.xml").
config.xml:
```
<?xml version="1.0"?>
<project>
    <name>myProject</name>
    <host>
        <address>localhost</address>
        <port>80</port>
    </host>
    <static>
        <path>static</path>
    </static>
</project>
```
