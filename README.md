# WebCrowler

A lightweight **web crawler written in C** that explores websites, discovers links, tracks visited URLs, builds a link graph, and handles crawling rules through `robots.txt`.

WebCrowler is designed as a modular learning project that demonstrates the core components behind web crawling systems, including URL queues, graph structures, duplicate detection, and crawler control logic.

## 🚀 Features

* 🌐 Crawl websites from a starting URL
* 🔗 Discover and process hyperlinks
* 📌 Track visited URLs to prevent duplicate crawling
* 📊 Build a graph representation of discovered pages
* 🤖 Support for `robots.txt` handling
* ⚡ Queue-based crawling system
* 🧩 Modular C code architecture

## 🏗️ Project Structure

```text
WebCrowler/
├── bin/
│   └── crawler              # Compiled executable
│
├── build/
│   ├── crawler.o
│   ├── graph.o
│   ├── main.o
│   ├── queue.o
│   ├── robots.o
│   └── visited.o
│
├── include/
│   ├── graph.h              # Graph definitions
│   ├── queue.h              # Queue definitions
│   ├── robots.h             # robots.txt handling
│   └── visited.h            # Visited URL tracking
│
├── src/
│   ├── crawler.c            # Core crawling engine
│   ├── graph.c              # Link graph implementation
│   ├── main.c               # Program entry point
│   ├── queue.c              # Crawl queue implementation
│   ├── robots.c             # robots.txt parser
│   └── visited.c            # URL history management
│
├── Makefile
├── LICENSE
└── README.md
```

## 🛠️ Requirements

Before building, make sure you have:

* GCC or Clang
* GNU Make
* Linux/macOS environment recommended

Check your installation:

```bash
gcc --version
make --version
```

## 🔨 Build

Clone the repository:

```bash
git clone https://github.com/ryucode2/WebCrowler.git
cd WebCrowler
```

Build the project:

```bash
make
```

The executable will be created:

```text
bin/crawler
```

## ▶️ Usage

Run the crawler with a starting URL:

```bash
./bin/crawler <url>
```

Example:

```bash
./bin/crawler https://example.com
```

## ⚙️ How It Works

WebCrowler follows a queue-based crawling approach:

1. A starting URL is added to the crawl queue.
2. The crawler retrieves the next URL.
3. The page is processed and links are extracted.
4. New URLs are checked against:

   * Previously visited URLs
   * Crawling restrictions
5. Valid URLs are added back into the queue.
6. Discovered relationships are stored in the graph.

Architecture:

```text
             Start URL
                 |
                 v
          +-------------+
          |    Queue    |
          +-------------+
                 |
                 v
          +-------------+
          |  Crawler    |
          +-------------+
            /        \
           v          v
    +-----------+  +-----------+
    |  Visited  |  |  Robots   |
    +-----------+  +-----------+
           |
           v
     +-----------+
     |   Graph   |
     +-----------+
```

## 🧪 Testing

Build a fresh version:

```bash
make clean
make
```

Run against a test page:

```bash
./bin/crawler https://example.com
```

## 🧹 Cleaning

Remove generated build files:

```bash
make clean
```

## 🤝 Contributing

Contributions are welcome.

1. Fork the repository
2. Create a new branch:

```bash
git checkout -b feature-name
```

3. Make your changes
4. Commit:

```bash
git commit -m "Add new feature"
```

5. Push your branch:

```bash
git push origin feature-name
```

6. Open a pull request

## 📜 License

This project is licensed under the MIT License. See the `LICENSE` file for details.

## 👤 Author

**ryucode2**

GitHub:
https://github.com/ryucode2

