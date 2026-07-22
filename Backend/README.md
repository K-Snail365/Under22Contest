# u22procon-2026 Backend

GCP プロジェクトID: `u22procon-2026`

## 開発環境 (Docker)

VS Code の **Dev Containers** 拡張機能を利用します。
プロジェクトを開き、**「Reopen in Container」** を実行して開発コンテナを起動してください。

## セットアップ (GCP 認証)

コンテナ起動後、GCP にログインします。

```sh
gcloud auth login
gcloud auth application-default login
```

## デプロイ

基本は `make deploy` を実行します。

```sh
make deploy TARGET_DIR=./cells/<CELL_NAME>
```

### 例
```sh
make deploy TARGET_DIR=./cells/example
```

## cellのローカル実行

ローカルcell実行機能を初めて利用する場合、またはDockerfile更新後は
**「Dev Containers: Rebuild Container」** を実行してください。

指定したcellをFunctions Frameworkで同時に起動し、Caddy経由で公開します。

```sh
make local CELLS="sample-1 sample-2"
```

アクセス先:

```text
http://localhost:8080/sample-1
http://localhost:8080/sample-2
```

リクエスト例:

```sh
curl -X POST \
  -H "Content-Type: application/json" \
  -d '{"key":"value"}' \
  http://localhost:8080/sample-1
```

`cells/`直下の全cellを起動する場合:

```sh
make local-all
```

公開ポートを変更する場合:

```sh
make local CELLS="sample-1 sample-2" PROXY_PORT=9000
```

`PROXY_PORT`を変更した場合は、必要に応じてDev Containersのポート転送へ
そのポートを追加してください。停止は起動中のターミナルで `Ctrl+C` を入力します。

生成された共通モジュール、requirements、Caddyfileを削除する場合:

```sh
make local-clean
```

ローカル実行の準備では各cellの依存パッケージを現在のPython環境へインストールします。
実GCPサービスを利用するcellは実データへアクセスする可能性があります。
