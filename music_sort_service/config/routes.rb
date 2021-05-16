#  frozen_string_literal: true

Rails.application.routes.draw do
  namespace :music_sort_service, path: 'music-sort-service' do
    namespace :v1 do
      post '', to: 'songs#create'
      get 'songs/show', to: 'songs#show'
      get 'albums/show', to: 'albums#show'
      get 'artists/show', to: 'artists#show'
      get 'genres/show', to: 'genres#show'
      patch 'songs/update', to: 'songs#update'
      delete 'songs/destroy', to: 'songs#destroy'
    end
  end
end
