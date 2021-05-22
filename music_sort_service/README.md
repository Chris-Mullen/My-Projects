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
bundle install
rails generate model Song title:String comments:String path:String album:references genre:references track:Integer disk:Integer
rails generate model Album title:String artist:references year:Integer total_tracks:Integer total_disks:Integer
rails generate model Artist title:String
rails generate model Genre title:String

rails generate controller Songs create update destroy show
rails generate controller Albums show
rails generate controller Artists show
rails generate controller Genres show

rails generate serializer Song title comments path artist album genre track disk
rails generate serializer Album title songs artist year tracks disks
rails generate serializer Artist title albums
rails generate serializer Genre title songs
```

## Steps to set up the database for development
```
export RAILS_ENV=test
rails db:create
rails db:environment:set RAILS_ENV=test
rails db:migrate
rails db:setup
```

## Running the service
```
rails server
```

## Automated testing
```
rspec
```

## Testing the service endpoints
### POST
```
curl --header "Content-Type: application/json" --request POST --data  '{"title":"Classical"}' http://localhost:3000/music-sort-service/v1/genres
curl --header "Content-Type: application/json" --request POST --data  '{"title":"Ludwig Van Beethoven"}' http://localhost:3000/music-sort-service/v1/artists
curl --header "Content-Type: application/json" --request POST --data  '{"title":"Symphonies","artist":"Ludwig Van Beethoven","year":"1808","tracks":"1","disks":"1"}' http://localhost:3000/music-sort-service/v1/albums
curl --header "Content-Type: application/json" --request POST --data  '{"title":"Symphony No.6 (1st movement)","artist":"Ludwig Van Beethoven","album":"Symphonies","track":"1","tracks":"1","disk":"1","disks":"1","genre":"Classical","comments":"","path":"~/GIT/PROJECTS/My-Projects/music_sort_service/demo/Symphony No.6 (1st movement).mp3"}' http://localhost:3000/music-sort-service/v1
```

### PATCH
```
curl --header "Content-Type: application/json" --request PATCH --data \ '{"title":"Title"}' localhost:3000/music-sort-service/songs/:song_id
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
