# MUSIC SORT SERVICE

This is a basic REST web service built using Ruby on Rails to serve as an example for future projects.
It functions as an interface to maintain a music library which is stored in an SQL database.

## Prerequisites
### Ruby Version
```
2.7
```

### Installed Gems
```
rails
```

## Steps to create the service
```
rails new music_sort_service --api -T
```

## Steps to set up the database
```
rails db:create
rails db:migrate
rails db:setup
```

## Running the service
```
bundle install
rails server
```

## Automated testing
```
rspec
```

## Testing the service endpoints
### POST
```
curl --header "Content-Type: application/json" --request POST --data \ '{"name":"Name","artist":"Artist","album":"Album","track_number":"1","total_track_number":"10","disk_number":"1","total_disk_number":"2","genre":"Genre","comments":"Comments","path":"~/Music/example.mp3"}' \
http://localhost:3000/music-sort-service
```

### PATCH
```
curl --header "Content-Type: application/json" --request PATCH --data \ '{"name":"Name"}' localhost:3000/music-sort-service/songs/:song_id
```

### GET
```
curl localhost:3000/music-sort-service/songs
curl localhost:3000/music-sort-service/artists/
curl localhost:3000/music-sort-service/artists/:artist
curl localhost:3000/music-sort-service/albums/
curl localhost:3000/music-sort-service/albums/:album
curl localhost:3000/music-sort-service/genres/
curl localhost:3000/music-sort-service/genres/:genre
curl localhost:3000/music-sort-service/songs/:song_id

curl localhost:3000/music-sort-service/songs?page[limit]=2&page[nextLink]=ffa850e5-9c4a-4bb9-b31d-19f07d5a6efd_2021-01-01T00:00:00Z

```

### DELETE
```
curl -X DELETE localhost:3000/music-sort-service/songs/:song_id
```
