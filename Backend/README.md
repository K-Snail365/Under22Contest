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