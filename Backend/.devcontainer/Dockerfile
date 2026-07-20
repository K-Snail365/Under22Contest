FROM mcr.microsoft.com/devcontainers/python:3.12-bookworm

USER root

ENV DEBIAN_FRONTEND=noninteractive
ENV CLOUDSDK_SKIP_PY_COMPILATION=1

RUN apt-get update \
  && apt-get install -y --no-install-recommends \
  make \
  curl \
  ca-certificates \
  gnupg \
  && mkdir -p /usr/share/keyrings \
  && curl -fsSL https://packages.cloud.google.com/apt/doc/apt-key.gpg \
  | gpg --dearmor -o /usr/share/keyrings/cloud.google.gpg \
  && echo "deb [signed-by=/usr/share/keyrings/cloud.google.gpg] https://packages.cloud.google.com/apt cloud-sdk main" \
  > /etc/apt/sources.list.d/google-cloud-sdk.list \
  && apt-get update \
  && apt-get install -y --no-install-recommends google-cloud-cli \
  && apt-get clean \
  && rm -rf /var/lib/apt/lists/*

USER vscode