#  frozen_string_literal: true

Rails.application.routes.draw do
  namespace :music_sort_service, path: 'music-sort-service' do
    namespace :v1 do
      get 'songs', to: 'songs#show_all'
      get 'albums', to: 'albums#show_all'
      get 'artists', to: 'artists#show_all'
      get 'genres', to: 'genres#show_all'
      post '', to: 'songs#create'
      post 'albums', to: 'albums#create'
      post 'artists', to: 'artists#create'
      post 'genres', to: 'genres#create'

      resources :songs, only: [] do
        get '', to: 'songs#show'
        patch 'update', to: 'songs#update'
        delete 'destroy', to: 'songs#destroy'
      end

      resources :albums, only: [] do
        get '', to: 'albums#show'
      end

      resources :artists, only: [] do
        get '', to: 'artists#show'
      end

      resources :genres, only: [] do
        get '', to: 'genres#show'
      end
    end
  end
end
